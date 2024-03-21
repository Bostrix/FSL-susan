#

#{{{ copyright etc.

#   susan_proc.tcl - TCL call for susan smoothing
#
#   Stephen Smith, Matthew Webster FMRIB Image Analysis Group
#
#   Copyright (C) 1999-2006 University of Oxford
#
#   TCLCOPYRIGHT

#}}}

proc susan_proc { input bt output dt dim um usans usanlist } {

    global FSLDIR

    #{{{ prepare thecommand

set thecommand "${FSLDIR}/bin/susan $input $bt $dt $dim $um $usans"

set i 1
while { $i <= $usans } {
    set thecommand "$thecommand [ lindex $usanlist [ expr ( $i - 1 ) * 2 ] ] [ lindex $usanlist [ expr ( ( $i - 1 ) * 2 ) + 1 ] ]"
    incr i 1
}

if { $usans > 0 } {
    set thecommand "$thecommand ${input}_usan_size"
}

set thecommand "$thecommand $output"

#}}}
    #{{{ call program

puts $thecommand

if { [ catch { exec sh -c $thecommand } ErrMsg ] != 0 } {
    puts "$ErrMsg"
}

puts Finished

#}}}
}
