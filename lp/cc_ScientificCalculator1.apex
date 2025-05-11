public class ScientificCalculator1 {

    public static Double evaluate(String expression) {
        expression = expression.trim().toLowerCase();

        try {
            // Handle arithmetic expressions like: 2 + 3
            if (expression.contains(' ')) {
                List<String> parts = expression.split(' ');
                if (parts.size() != 3) {
                    throw new CalloutException('Invalid expression format. Use format like: 2 + 3');
                }

                Double operand1 = Double.valueOf(parts[0]);
                String operator = parts[1];
                Double operand2 = Double.valueOf(parts[2]);

                if (operator == '+') {
                    return operand1 + operand2;
                } else if (operator == '-') {
                    return operand1 - operand2;
                } else if (operator == '*') {
                    return operand1 * operand2;
                } else if (operator == '/') {
                    if (operand2 == 0) {
                        throw new CalloutException('Cannot divide by zero');
                    }
                    return operand1 / operand2;
                } else if (operator == '^') {
                    return Math.pow(operand1, operand2);
                } else {
                    throw new CalloutException('Unsupported operator: ' + operator);
                }
            }

            // Handle scientific functions
            if (expression.startsWith('sin(')) {
                return Math.sin(toRadians(getInnerValue(expression)));
            } else if (expression.startsWith('cos(')) {
                return Math.cos(toRadians(getInnerValue(expression)));
            } else if (expression.startsWith('tan(')) {
                return Math.tan(toRadians(getInnerValue(expression)));
            } else if (expression.startsWith('sqrt(')) {
                return Math.sqrt(getInnerValue(expression));
            } else if (expression.startsWith('log(')) {
                return Math.log(getInnerValue(expression));
            } else if (expression.startsWith('exp(')) {
                return Math.exp(getInnerValue(expression));
            } else {
                throw new CalloutException('Unknown function or operator');
            }

        } catch (Exception e) {
            System.debug('Error: ' + e.getMessage());
            throw e;
        }
    }

    private static Double getInnerValue(String expr) {
        Integer startIndex = expr.indexOf('(');
        Integer endIndex = expr.indexOf(')');
        if (startIndex == -1 || endIndex == -1 || endIndex <= startIndex + 1) {
            throw new CalloutException('Invalid syntax for function: ' + expr);
        }
        String innerVal = expr.substring(startIndex + 1, endIndex).trim();
        return Double.valueOf(innerVal);
    }

    private static Double toRadians(Double degrees) {
        return degrees * Math.PI / 180;
    }
}
/*
 *System.debug('Addition: ' + ScientificCalculator1.evaluate('10 + 20'));
System.debug('Power: ' + ScientificCalculator1.evaluate('2 ^ 4'));
System.debug('Sine: ' + ScientificCalculator1.evaluate('sin(90)'));
System.debug('Square Root: ' + ScientificCalculator1.evaluate('sqrt(25)'));
System.debug('Natural Log: ' + ScientificCalculator1.evaluate('log(10)'));
System.debug('Exponent: ' + ScientificCalculator1.evaluate('exp(2)'));
*/