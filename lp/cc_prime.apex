public class prime {
    public static void main(){
		Integer num = 2;
        Boolean isPrime = true;
        for(Integer i = 2; i < Math.sqrt(num); i++){
            if(Math.mod(num, i) == 0) isPrime = false;
        }
        
        if(isPrime){
            System.debug('Is Prime');
        }
    }
}