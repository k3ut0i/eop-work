#!/usr/bin/perl
use strict;
use warnings;

use Test::More;
use IPC::Open3 qw(open3);
use Symbol 'gensym';
sub compare_tab_sep_vales{
  my ($expected, $got) = split;
  is($got, $expected);
}

sub test_program{
  my $program = shift(@_);
  my ($wtr, $rdr, $err);
  $err = gensym;
  my $pid = open3($wtr, $rdr, $err, $program);
  waitpid($pid, 0);
  my $child_status = $? >> 8;
  is($child_status, 0, "program ret val on exit");
  for (<$rdr>) {
    chomp; my ($expected, $got, $desc_str) = split(/ /);
    is($got, $expected, $desc_str);
  }
}

my $test_path = "./t/types_test";
subtest $test_path , sub{
  test_program("./t/types_test");
  done_testing();
};
done_testing();
1;
