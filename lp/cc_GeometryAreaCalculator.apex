public class GeometryAreaCalculator {
    public static Double calculateArea(String shape, Double value1, Double value2) {
        shape = shape.toLowerCase();
        Double area = 0.0;

        if (shape.equals('circle')) {
            area = Math.PI * value1 * value1;
        } else if (shape.equals('rectangle')) {
            area = value1 * value2;
        } else if (shape.equals('square')) {
            area = value1 * value1;
        } else if (shape.equals('triangle')) {
            area = 0.5 * value1 * value2;
        } else {
            System.debug('Invalid shape: ' + shape);
        }

        return area;
    }
}