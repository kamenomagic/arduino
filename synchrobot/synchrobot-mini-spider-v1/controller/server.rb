#! /usr/bin/env ruby
require 'rubyserial'
require 'sinatra'
require 'json'
serialport = Serial.new(ARGV.length == 0 ? '/dev/tty.usbserial-14220' : ARGV[0], 115200)
sleep(5)

post "/move" do
  command = JSON.parse(request.body.read)['command']
  serialport.write(command)
  puts "Move command: #{command}"
end

before do
  headers['Access-Control-Allow-Methods'] = 'GET, POST, PUT, DELETE, OPTIONS'
  headers['Access-Control-Allow-Origin'] = '*'
  headers['Access-Control-Allow-Headers'] = 'accept, authorization, origin'
end

options '*' do
  response.headers['Allow'] = 'HEAD,GET,PUT,DELETE,OPTIONS,POST'
  response.headers['Access-Control-Allow-Headers'] = 'X-Requested-With, X-HTTP-Method-Override, Content-Type, Cache-Control, Accept'
end
