use Win32::Scheduler;

tie( %Tasks, 'Win32::Scheduler', shift @ARGV ) || die "Unable to tie to machine's task list\n";

$~ = TaskDataFormat;

foreach my $Task ( keys( %Tasks ) )
{
    my $TaskData = $Tasks{$Task};

    print $Task, "\n";
    foreach $Attribute ( keys( %$TaskData ) )
    {
        $Value = $TaskData->{$Attribute};
        write;
    }

    print "\n";
}


print "Finished.\n";

format TaskDataFormat =
       @<<<<<<<<<<<<<<<<<<<<<<<<   ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
       "\u$Attribute",              $Value
~                                  ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                    $Value
~                                  ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                    $Value
~                                  ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                    $Value
.