# Project22
You have been asked to write a program to organize records in a library. Suppose all the records are stored in a data file called record.dat. Your program should read in the information from this data file and then group them on the basis of book types. Finally, your program should print out the grouped information to an output file called grouped_record.dat. You should use a struct to store the information for each book, which contains 
Publication_date  (data type: another struct) 
Author (data type: another struct) 
Title ( data type: string) 
Cost (data type: float) 
Type (data type: integer;   1 – science book, 2 – arts book, 3 – language book, 4 – all
other books)
The record for publication date should contain the following information: Day (data type: integer) Month (data type: integer) Year (data type: integer) The record for Author should contain First_name (data type: string) Middle_name (data type: string) Last_name (data type: string) A typical input data file looks like: 
[1 8 1993 
Margaret Dana Mitchell 
Gone with the wind 
7.19 
3 
1 12 1995 
Mario C. Puzo 
The godfather 
7.99 
3]

An array of struct should be used to hold the information of all the books in the data file. When your program writes the information of grouped books to the output file,  output the  information of books with book type 1 firstly, type 2 secondly, and so on. To provide solutions to this project, you need to deliver the following components on the basis of principles in software engineering.
