class Main{
    public static void main(Strings[] args){
        ganttChart(new int {1,2,3,4});    
    
    }

    public static void ganttChart(int[] array){
        for (int i = 0; i < array.length; i++) {
        //System.out.print("|");
        for (int j = 0; j < array[i]; j++) {
            System.out.print("__");
            }
        }
        System.out.println();

    
        for (int i = 0; i < array.length; i++) {
            System.out.print("|");
            for (int j = 0; j < array[i]; j++) {
                if (j == array[i] / 2) {
                    System.out.print(array[i] + " ");
                    if (array[i] >= 10) j++; 
                } else {
                    System.out.print("  ");
                }
            }
        }
        System.out.println("|");
         for (int i = 0; i < array.length; i++) {
            System.out.print("|");
            for (int j = 0; j < array[i]; j++) {
                System.out.print("__");
            }
         }
      System.out.println("|");

    }
}