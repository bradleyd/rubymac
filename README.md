# Rubymac

Returns mac address for a Ethernet device on nix system

## Installation

Add this line to your application's Gemfile:

    gem 'rubymac'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install rubymac

## Usage
* This is a simple ruby library that will return a mac address from the machine it is running on.
* This is no way feature complete and fully tested on many systems.

To get your mac address:
  $ mac_addr = RubyMac.new
  $ mac_addr.address("eth0")
  $ "d48564095de2"

## Contributing

* Please make any changes you like and send me a request.

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Added some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
