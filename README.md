## Implementation of heap


## Group Info
UFID: 8115 5459 Shaileshbhai Revabhai Gothi

UFID: 1451 4662 Siddardha Majety 


## Using the driver

1. SETTINGS: The following variables control the various file locations and they are declared in test.cc (just after the #include header declarations):
	o dbfile_dir -- this is where the created heap db-files will be stored. By default, this is set to "" (thus all the heap dbfiles will be created in the current directory).
	o tpch_dir -- this stores the directory path where the tpch-files can be found. By default, tpch_dir is set to "/cise/tmp/dbi_sp11/DATA/10M/". **Please change this path according to location of your tpch_dir.**
	o catalog_path -- this stores the catalog file path. By default this is set to "". **Please change this path according to location of your catalog.**

2. Once load of a file has been selected, you can select option 2 or 3 to scan/filter all the records from the heap DBfile.  If option 3 is selected, a CNF should be supplied. Some example CNF's are given below. They are numbered q1,q2..q12. Use the table below to identify the tpch file associated with each CNF.
     	table    |   CNF
 ---------------------------------------
        region    |  q1 q2   
        nation    |  q3   
        supplier  |  q4 q5
        customer  |  q6
        part      |  q7   
        partsupp  |  q8 q9
        orders    |  q10                
        lineitem  |  q11 q12 

The expected output for these CNF's can be found in the file "output.log"

### Example CNF's

q1 
(r_name = 'EUROPE')

q2 
(r_name < 'middle east') AND
(r_regionkey > 1)

q3 
(n_regionkey = 3) AND
(n_nationkey > 10) AND
(n_name > 'japan')

q4 
(s_suppkey < 10)

q5
(s_nationkey = 18) AND
(s_acctbal > 1000) AND
(s_suppkey < 400)

q6
(c_nationkey = 23) AND
(c_mktsegment = 'FURNITURE') AND
(c_acctbal > 7023.99) AND
(c_acctbal < 7110.83)


q7 
(p_brand = 'Brand#13') AND
(p_retailprice > 500) AND
(p_retailprice < 930) AND
(p_size > 28) AND
(p_size < 1000000)

q8 
(ps_supplycost > 999.98)

q9 
(ps_availqty < 10)
(ps_supplycost > 100) AND
(ps_suppkey < 300) AND

q10 
(o_orderpriority = '1-URGENT') AND
(o_orderstatus = '0') AND
(o_shippriority = 0) AND
(o_totalprice > 1015.68) AND
(o_totalprice < 1051.89)

q11
(l_shipdate > '1994-01-01') AND
(l_shipdate < '1994-01-07') AND
(l_discount > 0.05) AND
(l_discount < 0.06) AND
(l_quantity = 4.0) 


q12
(l_orderkey > 100) AND
(l_orderkey < 1000) AND
(l_partkey > 100) AND
(l_partkey < 5000) AND
(l_shipmode = 'AIR') AND
(l_linestatus = 'F') AND
(l_tax < 0.07)



## How to run

Unzip the contents/pull from bitbucket and run the below command

```bash
# generate test.out using 
make -B
# Run test.out and follow the instructions on console.
./test.out 

# generate executeTests.out using 
make -B executeTests.out
# Run All test cases.
./executeTests.out 

# generate main using 
make -B main
# Run main file and provide CNF.
./main

```




