#!/usr/bin/perl -w

open (F, "<bigtest.txt") or die "CANNOT OPEN FILE";
my $count = 0;
while (my $line = <F>) {
   open (D, ">bigtest$count.txt") or die "Cannot make file";
   chomp $line;
   $line =~ s/ /\n/g;
   print D $line;
   close D;
   $count += 1;
}
close F;
