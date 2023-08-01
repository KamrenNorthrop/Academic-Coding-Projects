class PA3Main
{
  public static void main(String[] args)
  {
    Vector a,b,c,i,j,k;
    a=new Vector(1,1,1);
    b=new Vector(3,4,0);
    c=a.add(b);
    System.out.println("a (1,1,1)=" + a + " b(3,4,0)=" + b + " sum=" + c);

    c=a.sub(b);
    System.out.println("difference=" + c);

    System.out.println("length of a=" + a.length());
    System.out.println("length of b=" + b.length());
    c=a.sub(a); // this is the zero vector
    System.out.println("c (0,0,0)=" + c + " length=" + c.length());

// normalize
    System.out.println("a normalized=" + a.normalize());
    System.out.println("b normalized=" + b.normalize());
    System.out.println("c normalized=" + c.normalize());

// get components
    b=new Vector(3,4,5);
    System.out.println("Components of (3,4,5) are " + b.x() + " " + b.y()
                        + " " + b.z());

// scale
    System.out.println("b(3,4,5)*7=" + b.multiply(7));

// dot product
    System.out.println(a + "dot" + b + "=" + a.multiply(b));
    System.out.println(b + "dot" + a + "=" + b.multiply(a));
  }
}
