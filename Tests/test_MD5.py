"""
uint32_t digest[4] = { 0 };
MD5(argv[1], strlen(argv[1]), digest);

uint8_t* dig = (uint8_t*)(digest);
for (int i = 0; i < 16; i++)
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

for length in range (1, 50000):
	print 'Len = ', length
	s = get_rand_str(length)
	res = os.popen(exe_path + ' ' + s).read().strip()
	if hashlib.md5(s).hexdigest() != res:
		print 'Difference on length {}, with string {}\n    MD5: {}\n    RES: {}'.format(length, s, hashlib.md5(s).hexdigest(), res)
