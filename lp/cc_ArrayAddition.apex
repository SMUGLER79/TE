public class ArrayAddition {

    // Method to add two arrays element-wise
    public static List<Integer> addArrays(List<Integer> array1, List<Integer> array2) {
        if (array1.size() != array2.size()) {
            throw new IllegalArgumentException('Arrays must be of the same size.');
        }

        List<Integer> result = new List<Integer>();
        for (Integer i = 0; i < array1.size(); i++) {
            result.add(array1[i] + array2[i]);
        }
        return result;
    }
}
/*
 List<Integer> arr1 = new List<Integer>{1, 2, 3, 4, 5};
List<Integer> arr2 = new List<Integer>{10, 20, 30, 40, 50};

List<Integer> result = ArrayAddition.addArrays(arr1, arr2);
System.debug('Array 1: ' + arr1);
System.debug('Array 2: ' + arr2);
System.debug('Result (Sum): ' + result);
*/