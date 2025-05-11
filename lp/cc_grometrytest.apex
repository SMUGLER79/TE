public class GeometryTest {
    public static void run() {
        System.debug('Circle Area: ' + GeometryAreaCalculator.calculateArea('circle', (Double)3.0, (Double)null));
        System.debug('Rectangle Area: ' + GeometryAreaCalculator.calculateArea('rectangle', (Double)4.0, (Double)5.0));
        System.debug('Square Area: ' + GeometryAreaCalculator.calculateArea('square', (Double)4.0, (Double)null));
        System.debug('Triangle Area: ' + GeometryAreaCalculator.calculateArea('triangle', (Double)3.0, (Double)6.0));
        System.debug('Invalid Shape: ' + GeometryAreaCalculator.calculateArea('hexagon', (Double)3.0, (Double)6.0));
    }
}