#!/usr/bin/env ruby

File.read(ARGV[0]).each_line do |l|
  next if l[0] == 'c'

  if l[0] == 'p'
    p, _, v, e = l.split
    puts "#{v} #{e}"
  elsif l[0] == 'e'
    e, v1, v2 = l.split
    puts "#{v1.to_i - 1} #{v2.to_i - 1}"
  end
end
