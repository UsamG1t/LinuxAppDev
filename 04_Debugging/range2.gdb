set pagination off
set logging file range2.output
set logging on	

b 38 if (count >= 28 && count <= 35)
	command 1
        print i
        print start
        print stop
        print step
        cont
	end

set args -100 100 3
run

quit