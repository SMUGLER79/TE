public class MatrixMultiplication {

    // Method to multiply two matrices
    public static List<List<Integer>> multiplyMatrices(List<List<Integer>> matrixA, List<List<Integer>> matrixB) {
        Integer rowsA = matrixA.size();
        Integer colsA = matrixA[0].size();
        Integer rowsB = matrixB.size();
        Integer colsB = matrixB[0].size();

        if (colsA != rowsB) {
            System.debug('Matrix multiplication not possible');
            return null;
        }

        // Initialize result matrix
        List<List<Integer>> result = new List<List<Integer>>();
        for (Integer i = 0; i < rowsA; i++) {
            List<Integer> row = new List<Integer>();
            for (Integer j = 0; j < colsB; j++) {
                row.add(0);
            }
            result.add(row);
        }

        // Matrix multiplication logic
        for (Integer i = 0; i < rowsA; i++) {
            for (Integer j = 0; j < colsB; j++) {
                for (Integer k = 0; k < colsA; k++) {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }

        return result;
    }

    // Entry method
    public static void runMatrixMultiplication() {
        List<List<Integer>> matrixA = new List<List<Integer>>{
            new List<Integer>{1, 2},
            new List<Integer>{3, 4}
        };

        List<List<Integer>> matrixB = new List<List<Integer>>{
            new List<Integer>{5, 6},
            new List<Integer>{7, 8}
        };

        List<List<Integer>> result = multiplyMatrices(matrixA, matrixB);

        if (result != null) {
            System.debug('Result of Matrix Multiplication:');
            for (List<Integer> row : result) {
                System.debug(row);
            }
        }
    }
}

//MatrixMultiplication.runMatrixMultiplication();