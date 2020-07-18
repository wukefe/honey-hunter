import sys
import time
import fileinput

def main():
    if len(sys.argv) != 1:
        print "Usage: python cut.py <std_input>"
        sys.exit(1)
    lineno = 0
    for line in fileinput.input():
    	line = line.strip('| \r\n').split('|')
        if lineno % 5 == 2:
            print (0 if line[0].strip() == 'null' else float(line[0]))
        lineno = lineno + 1
    pass

if __name__ == '__main__':
    #start = time.time()
    main()
    #sys.stderr.write('Elapsed time: %g ms\n' % (1000*(time.time() - start)))
