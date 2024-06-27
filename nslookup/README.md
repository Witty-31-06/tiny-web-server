# Build Instructions

The ELF file in this folder was built by compiling nslookup_clone.c. The flags I used during compiling are mentioned in the Makefile. To build the ELF file, run the following command in the terminal:

cd into the directory containing nslookup_clone.c and the Makefile and run the following command:

```bash
make
./nslookup_clone <domain_name>
```