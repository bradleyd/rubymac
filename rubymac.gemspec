# -*- encoding: utf-8 -*-
require File.expand_path('../lib/rubymac/version', __FILE__)

Gem::Specification.new do |gem|
  gem.authors       = ["Brad Smith"]
  gem.email         = ["bradleydsmith@gmail.com"]
  gem.description   = %q{Returns the mac address on Nix* system.}
  gem.summary       = %q{Returns the mac address on a Nix* system.}
  gem.homepage      = ""

  gem.extensions    = ['ext/rubymac/extconf.rb'] 
  gem.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  gem.files         = `git ls-files`.split("\n")
  gem.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  gem.name          = "rubymac"
  gem.require_paths = ["lib", "ext"]
  gem.version       = Rubymac::VERSION
end
