## PushDB: An updated approach to Database
___


### Philosophy
This is an experimental database, primarily to implement an updated approach to [The DataPath system: a data-centric analytic processing engine for large data warehouses](https://dl.acm.org/doi/abs/10.1145/1807167.1807224), work presented in 2010 by _Arumugam et. al_.

### Depends on
This will run on most GNU/Linux systems, without providing root privilages.
Any deviation from this behavior is welcome to be reported.

### Clone
```bash
# HTTPS
git clone --recursive https://gitlab.com/r0ck3r008/pushdb.git
# SSH
git clone --recursive git@gitlab.com:r0ck3r008/pushdb.git
```
### Compilation Instructions
```bash
# Compile
make
# Clean
make clean
# Deep clean
make distclean
```
### Execution Instructions
```bash
./bin/pushdb.out <options>
```
#### Commandline Arguments
* -h, --help:
	* Show the available options and switches
* -i, --ifile:
	* Path to input file to read query from
	* default is stdin
* -o, --ofile:
	* Path to output file logger messages
	* default is stdout
* -v, --verb
	* Verbosity of the logger, LOG_ERR=0, LOG_WRN=1 and LOG_DBG=2
	* default is 0
* -s, --single
	* Single query input switch, exists after executing single query if on
	* Default off
