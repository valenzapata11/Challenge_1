# CHALLENGE 2
#### Valentina Zapata Coronel 10985360
The following code presents a possible implementation of a sparse matrix.
The matrix is built under a class called Matrix (<Data_type, StorageOrder>) in the namespace algebra. To define it the user must state the data type and the desired
Storage Order (0 for row-wise storage and 1 for column-wise storage). 

The class allows the user to:
- Compress/Uncompress the matrix
- Fill matrix from .mtx file
- Access elements with operator ()
- Vector Matrix multiplication
- Matrix Matrix multiplication (Only when the first matrix only has one column)

The matrix can be created empty, or the user can state the size beforehand. 
## 
The main file is used to show potential uses of the built class.

Efficiency was tested for the vector * Matrix multiplication under the cases: compressed/ uncompressed and row/column-wise storage. Results showed more efficiency in computing the operation in the compressed state. 
