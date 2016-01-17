CSV Template Merger
===================

Random Level Generator and Level Script Compiler for Super Mario Bros. 1 on the NES

-===========================- About CSV Template Merger -===========================-

 This is a simple program I wrote for work to help with keeping our CSV data files
 at a small size. The idea is to break up redundant rows into templates and "ID files".

 For example:
 -===========================-
 ID File Contains:
 ID
 1
 2
 3

 Template File Contains:
 Name,City
 Bob,SF
 Sue,LA

 The output file will be:
 ID,Name,City
 1,Bob,SF
 1,Sue,LA
 2,Bob,SF
 2,Sue,LA
 3,Bob,SF
 3,Sue,LA
 -===========================-

 Keep in mind that the ID file can contain multiple columns if necessary.

 If a column header in the ID file matches a column header in the template file,
 the contents of that column will be replaced with the new data. If the column
 header in the ID file does not match a column header in the template file,
 the new data will simply be preappended.

 The application can be run with no arguments for a GUI or can be run over command line
 using the following syntax:
 CSV_Template_Merger.exe <ID_file> <template_file> <output_file>

 Windows, Mac, and Linux users should compile the application through QtCreator.
 As I highly doubt many people will find use of this application, I do not intend to maintain
 binaries. If you need a binary and you are unable to compile the application, feel
 free to contact me.
 
 All code in this repository is released under the GPLv2 License.
 
 If you have any questions about CSV Template Merger, feel free to contact me at coolcord24@gmail.com