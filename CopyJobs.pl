#
#   CopyJobs.pl
#
#   This will copy all scheduled tasks from one machine to another.
#

use Win32::Scheduler;

die Syntax() if( 2 > scalar @ARGV );
$Machine{dst} = shift @ARGV;
$Machine{src} = shift @ARGV;

tie( %Destination, 'Win32::Scheduler', $Machine{dst} ) || die "Unable to connect to '$Machine{dst}'.";
tie( %Source, 'Win32::Scheduler', $Machine{src} ) || die "Unable to connect to '$Machine{src}'.";

print "Copying scheduled jobs from $Machine{src} to $Machine{dst}...\n";

%Destination = %Source;

print "Finsihed.\n";

untie %Source;
untie %Destination;

sub Syntax
{
    my $String = "Syntax: $0 <DestinationMachine> <SourceMachine>\n";
    return( $String );
}