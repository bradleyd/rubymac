require 'test/unit'
require 'rubymac'

class RubyMacTest < Test::Unit::TestCase
  def test_bad_interface
    assert_equal false, RubyMac.new.address("eth3")
  end

  def test_good_interface
    @mac = RubyMac.new
    assert_equal true, @mac.address("eth0").is_a?(String)
  end

end
