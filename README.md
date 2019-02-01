# Project ft_ssl_md5

# Personal implementation of 3 hashing algorithms:
  * md5
  * sha256
  * sha224

# Usage:

./ft_ssl command [command options] [command args]

## Commands

Available commands are "md5", "sha256" and "sha224"

## Command options

  * "-p" -> Reads from STDIN. Outputs text to hash, and the hash in a new line.
  * "-s" -> ./ft_ssl takes a string as a parameter and not a file.
  * "-q" -> Quiet mode: outputs only the hash (Message Digest).
  * "-r" -> Reverse: outputs hash first, file path or string after.

## Examples

echo "test" > file.txt  
./ft_ssl md5 file.txt  

./ft_ssl sha256 -s "Some example"  

echo "test 1" > file1.txt  
echo "test 2" > file2.txt  
echo "test 3" > file3.txt  
./ft_ssl md5 file1.txt file2.txt file3.txt  
