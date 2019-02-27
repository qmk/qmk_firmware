#!/usr/bin/env ruby

class KeymapConverter

  def initialize(filename)
    @filename = filename
    @mode = :search
  end

  def read_keymaps
    lines = IO.readlines(@filename)
    lines.each { |line| parse_line line[0..-2] }
  end

  def parse_line(line)
    case @mode
    when :search
      if line =~ /KC_KEYMAP/
        puts "### #{line}"
        puts "```"
        @mode = :parse
      end
    when :parse
      if line =~ /\)/
        @mode = :search
        puts "```\n\n"
      else 
        line = line[4..-1]
        line.sub!(/(,)^-/m, "|")
        line.sub!(/( {4})/, "    |")

        puts line
      end
    end
  end

end

converter = KeymapConverter.new('keymap.c')
converter.read_keymaps
