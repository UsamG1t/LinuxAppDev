set pagination off
set logging file range1.output
set logging on	

b 29 if i % 5 == 0
	command 1
        print i
        print start
        print stop
        print step
        cont
	end

set args 1 12
run

quit