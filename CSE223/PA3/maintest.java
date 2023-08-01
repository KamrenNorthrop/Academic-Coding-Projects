class Main{
	public static void main(String[] args){
		Vector v1 = new Vector(1,2,3);
		Vector v2 = new Vector(4,5,6);
	        Vector v3 = new Vector(0,0,0);	
		Vector v4 = new Vector(1,2,3);	
		System.out.println("v1:"+v1);
		System.out.println("v2:"+v2);
		System.out.println("v3:"+v3);
		System.out.println("V4:"+v4);
		System.out.println();		

		Vector c = v1.add(v2);
		Vector d = v1.sub(v2);
		Vector e = v1.multiply(3.0);
		double f = v1.multiply(v2);
		double g = v1.length();
		Vector h = v1.normalize();
		Vector I = v3.normalize();
		Vector test = v1.add(v4);

		System.out.println("C(add)-> V1+V2:"+c);
		System.out.println("test: v1+v4"+test);

		System.out.println("D(sub)-> V1-V2:"+d);
		System.out.println("E(multiplication by scalar-> V1*3.0):"+e);
		System.out.println("F(Multi Vectors-> V1*V2):"+f);
		System.out.println("G(Length)-> V1:"+g);	
		System.out.println("H(Normalized)-> V1:"+h);
		System.out.println("I(Normalized)-> V3:"+I);
	}


}
