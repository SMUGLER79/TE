public class Fibbo {
    public static void main(){
     	Integer num1 = 0;
        Integer num2 = 1;
        System.debug('Fibbonacci Series: ');
        
        for(Integer i = 0; i < 5; i++){
            System.debug(num1);
            Integer next = num1 +num2;
            num1 = num2;
            num2 = next;
        }
    }
}