#!/usr/bin/env ruby
# frozen_string_literal: true

require "yaml"
require "fileutils"
require "pathname"
require "set"

class ThemeBuilder
  PLACEHOLDER = "#facade"
  BATTERY_OUTER = "#fade01"
  BATTERY_INNER = "#fade02"

  BATTERY_LEVELS = %w[20 40 60 80 100].freeze

  FALLBACK_KEYS = %w[accent surface].freeze
  EXTERNAL_KEYS = %w[bg].freeze

  HEX_COLOR = /\A#[0-9a-fA-F]{6}\z/

  HEADER_NAME = "Theme.h"

  class Error < StandardError; end

  def initialize(config_path:, assets_dir:, output_dir:)
    @config_path = Pathname.new(config_path).expand_path
    @assets_dir = Pathname.new(assets_dir).expand_path
    @output_dir = Pathname.new(output_dir).expand_path
    @used_keys = Set.new
  end

  def build!
    config = load_config
    defaults = config.fetch("default")
    themes = config.fetch("themes")

    validate_config!(config, defaults, themes)
    validate_assets!

    outputs = {}
    themes.each do |name, overrides|
      outputs.merge!(render_theme(name, defaults.merge(overrides)))
    end

    current = config["current"] || themes.keys.first
    outputs[@output_dir.join(HEADER_NAME)] =
      outputs.fetch(@output_dir.join(current, HEADER_NAME))

    FileUtils.rm_rf(@output_dir)
    outputs.each do |path, content|
      FileUtils.mkdir_p(path.dirname)
      path.write(content)
    end

    themes.each_key { |name| puts "Built theme: #{name}" }
    warn_unused_keys(defaults, themes)
  end

  private

  def load_config
    raise Error, "Config not found: #{@config_path}" unless @config_path.file?

    config = YAML.safe_load_file(
      @config_path,
      permitted_classes: [],
      permitted_symbols: [],
      aliases: false
    )

    raise Error, "Config root must be a mapping" unless config.is_a?(Hash)
    raise Error, "Missing 'default' mapping" unless config["default"].is_a?(Hash)
    raise Error, "Missing 'themes' mapping" unless config["themes"].is_a?(Hash)
    raise Error, "At least one theme is required" if config["themes"].empty?

    config
  rescue Psych::Exception => e
    raise Error, "Invalid YAML: #{e.message}"
  end

  def validate_config!(config, defaults, themes)
    validate_colors!(defaults, "default")

    themes.each do |name, overrides|
      unless name.is_a?(String) &&
          name.match?(/\A[a-zA-Z0-9_-]+\z/)
        raise Error, "Invalid theme name: #{name.inspect}"
      end

      unless overrides.is_a?(Hash)
        raise Error, "Theme '#{name}' must be a mapping"
      end

      validate_colors!(overrides, "themes.#{name}")
    end

    current = config["current"]
    if current && !themes.key?(current)
      raise Error, "'current' references undefined theme: #{current}"
    end
  end

  def validate_colors!(mapping, location)
    mapping.each do |key, value|
      unless key.is_a?(String)
        raise Error, "#{location}: color keys must be strings"
      end

      unless value.is_a?(String) && HEX_COLOR.match?(value)
        raise Error,
          "#{location}.#{key}: expected a quoted #RRGGBB color, got #{value.inspect}"
      end
    end
  end

  def validate_assets!
    raise Error, "Assets directory not found: #{@assets_dir}" unless @assets_dir.directory?

    files = svg_files
    raise Error, "No SVG assets found in #{@assets_dir}" if files.empty?

    files.each do |path|
      next unless battery_asset?(asset_key(path))

      content = path.read
      unless has_color?(content, BATTERY_OUTER) &&
          has_color?(content, BATTERY_INNER)
        raise Error,
          "#{path}: battery SVG must contain #{BATTERY_OUTER} and #{BATTERY_INNER}"
      end
    end
  end

  def render_theme(name, colors)
    theme_dir = @output_dir.join(name)

    files = svg_files.to_h do |source|
      key = asset_key(source)
      content = source.read

      if battery_asset?(key)
        content = replace_color(content, BATTERY_OUTER, required_color(colors, "#{key}_outer", source))
        content = replace_color(content, BATTERY_INNER, required_color(colors, "#{key}_inner", source))
      elsif has_color?(content, PLACEHOLDER)
        content = replace_color(content, PLACEHOLDER, required_color(colors, key, source))
      end

      [theme_dir.join(source.relative_path_from(@assets_dir)), content]
    end

    files[theme_dir.join(HEADER_NAME)] = render_header(name, colors)
    files
  end

  def has_color?(content, placeholder)
    content.match?(placeholder)
  end

  def replace_color(content, placeholder, color)
    content.gsub(placeholder, color)
  end

  def required_color(colors, key, source)
    @used_keys << key
    color = colors[key]

    if color.nil?
      fallback = fallback_key(key)
      if fallback
        @used_keys << fallback
        color = colors[fallback]
      end
    end

    color || raise(Error, "#{source}: no color configured for '#{key}'")
  end

  def fallback_key(key)
    return "accent" if key.end_with?("_icon", "_txt")
    return "surface" if key.end_with?("_bg")

    nil
  end

  def warn_unused_keys(defaults, themes)
    configured = defaults.keys | themes.values.flat_map(&:keys)
    unused = configured - @used_keys.to_a - FALLBACK_KEYS - EXTERNAL_KEYS
    return if unused.empty?

    warn "Warning: keys not used by any asset: #{unused.join(', ')}"
  end

  def battery_asset?(key)
    BATTERY_LEVELS.any? { |level| key == "battery_#{level}" }
  end

  def asset_key(path)
    basename = path.basename(".svg").to_s

    case basename
    when "menu_home", "menu_extra"
      "menu_txt"
    else
      basename
    end
  end

  def svg_files
    @svg_files ||= @assets_dir.glob("**/*.svg").sort
  end

  def render_header(name, colors)
    lines = EXTERNAL_KEYS.map do |key|
      color = colors[key] or
        raise Error, "theme '#{name}': no color configured for external key '#{key}'"
      "constexpr unsigned #{key.upcase}_COLOR = 0x#{color.delete_prefix('#').downcase};"
    end

    ["#pragma once", "", "// generated, theme: #{name}", *lines, ""].join("\n")
  end
end

#┌─────────────────────────────────────────────────────────────────────────────┐#
#│                                   MAIN                                      │#
#└─────────────────────────────────────────────────────────────────────────────┘#

if $PROGRAM_NAME == __FILE__
  begin
    root = Pathname.new(__dir__)

    ThemeBuilder.new(
      config_path: root.join("theme.yml"),
      assets_dir: root.join("templates"),
      output_dir: root.join("build", "themes")
    ).build!
  rescue ThemeBuilder::Error => e
    warn "Theme build failed: #{e.message}"
    exit 1
  end
end
