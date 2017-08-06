"""
uint32_t digest[5] = { 0 };
SHA1(argv[1], strlen(argv[1]), digest);

uint8_t* dig = (uint8_t*)(digest);
for (int i = 0; i < 20; i++)
{
	printf("%02x", (*dig));
	dig++;
}

return 0;
"""


import sys, os, hashlib, string, random
exe_path = sys.argv[1]

def get_rand_str(length):
	s = ''
	for x in range(length):
		s += random.choice(string.letters)
	return s

for length in range (1, 2000):
	print 'Len = ', length
	s = get_rand_str(length)
	res = os.popen(exe_path + ' ' + s).read().strip()
	actual = hashlib.sha1(s).hexdigest()
	if actual != res:                                                                            
		print 'Difference on length {}, with string {}\n    SHA1: {}\n    RES : {}'.format(length, s, actual, res)
		exit(0)
print 'All test passed!'
