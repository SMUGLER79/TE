public class Interest {
    public Decimal SimpleInterest(Integer P, Integer R, Integer T){
		return (P*R*T)/100;
    }
    
    public Decimal CompoundInterest(Decimal P, Decimal R, Decimal T){
        Decimal compound = P.doubleValue() * Math.pow(1 + (R.doubleValue() /100), T.doubleValue());
		return (compound - P);
    }
    public static void run(){
        Interest i = new Interest();
        System.debug('Simple ' + i.SimpleInterest(10000, 5, 2)); 
        System.debug('Compound ' + i.CompoundInterest(10000, 5.0, 2));
	}
}

//Interest.run();