import sys

#PYTHON3

if len( sys.argv ) < 1:
	print("give filename as arg1")
else:
	with open(sys.argv[1], 'r') as fp:
		data=fp.read().replace( '\n',' ' ).lower()
		for cind in range( len(data) ):
			if data[cind] <= 'z' and data[cind] >= 'a' or data[cind] == ' ':
				print( data[cind], end='')
