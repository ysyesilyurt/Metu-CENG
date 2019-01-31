a=raw_input()
x=a.find("?")
def g(s):
	if 2*int(s)<10:
		return 2*int(s)
	else:
		return int(str(2*int(s))[0])+int(str(2*int(s))[1])
if x ==-1:
	y=int(a[0])+g(a[1])+int(a[2])+g(a[3])+int(a[4])+g(a[5])+int(a[7])
	if y%10==0:
		print "VALID"
	else: 
		print "INVALID"
if x ==0:
	c=g(a[1])+int(a[2])+g(a[3])+int(a[4])+g(a[5])+int(a[7])
	t=(c/10+1)*10
	print str((t-c)%10)+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]
if x ==1:
	d=int(a[0])+int(a[2])+g(a[3])+int(a[4])+g(a[5])+int(a[7])
	t=(d/10+1)*10
	if (t-d)%10==0 or (t-d)%10==2 or (t-d)%10==4 or (t-d)%10==6 or (t-d)%10==8:
		print a[0]+str(((t-d)%10)/2)+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]
	else:
		d=int(a[0])+int(a[2])+g(a[3])+int(a[4])+g(a[5])+int(a[7])
		t=(d/10+1)*10
		h=int("1"+str(((t-d)%10)-1))/2
		print a[0]+str(h)+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]
if x ==2:
	u=int(a[0])+g(a[1])+g(a[3])+int(a[4])+g(a[5])+int(a[7])
	t=(u/10+1)*10
	print a[0]+a[1]+str((t-u)%10)+a[3]+a[4]+a[5]+a[6]+a[7]
if x ==3:
	l=int(a[0])+g(a[1])+int(a[2])+int(a[4])+g(a[5])+int(a[7])
	t=(l/10+1)*10
	if (t-l)%10==0 or (t-l)%10==2 or (t-l)%10==4 or (t-l)%10==6 or (t-l)%10==8:
		print a[0]+a[1]+a[2]+str(((t-l)%10)/2)+a[4]+a[5]+a[6]+a[7]
	else:
		l=int(a[0])+g(a[1])+int(a[2])+int(a[4])+g(a[5])+int(a[7])
		t=(l/10+1)*10
		h=int("1"+str(((t-l)%10)-1))/2
		print a[0]+a[1]+a[2]+str(h)+a[4]+a[5]+a[6]+a[7]
if x ==4:
	w=int(a[0])+g(a[1])+int(a[2])+g(a[3])+g(a[5])+int(a[7])
	t=(w/10+1)*10
	print a[0]+a[1]+a[2]+a[3]+str((t-w)%10)+a[5]+a[6]+a[7]
if x ==5:
	n=int(a[0])+g(a[1])+int(a[2])+g(a[3])+int(a[4])+int(a[7])
	t=(n/10+1)*10
	if (t-n)%10==0 or (t-n)%10==2 or (t-n)%10==4 or (t-n)%10==6 or (t-n)%10==8:
		print a[0]+a[1]+a[2]+a[3]+a[4]+str(((t-n)%10)/2)+a[6]+a[7]
	else:
		n=int(a[0])+g(a[1])+int(a[2])+g(a[3])+int(a[4])+int(a[7])
		t=(n/10+1)*10
		h=int("1"+str(((t-n)%10)-1))/2	
		print a[0]+a[1]+a[2]+a[3]+a[4]+str(h)+a[6]+a[7] 
if x ==7:
	k=int(a[0])+g(a[1])+int(a[2])+g(a[3])+int(a[4])+g(a[5])
	t=(k/10+1)*10
	print a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+str((t-k)%10)
