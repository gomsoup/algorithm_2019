import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.locks.ReentrantLock;

class asdf{
        public int pos = 0;
        public ArrayList<Integer> idx = new ArrayList<Integer>();

        public final int allDist()
        {
            int dist = 0;
            for (int it : idx)
            {
                dist += Math.abs(pos - it);
            }

            return dist;
        }
}

public class audio{
    public static int n;
    public static ArrayList<ArrayList<Integer>> g = new ArrayList<ArrayList<Integer>>();
    public static ArrayList<Integer> result = new ArrayList<Integer>();
    public static ReentrantLock lock = new ReentrantLock();
    public static int minDist = 999999;


    public static int calc(ArrayList<Integer> array){
        int dist = 0;
        ArrayList<ArrayList<Integer>> gg = new ArrayList<ArrayList<Integer>>();
        for(int i = 0; i<n; i++){
            ArrayList<Integer> a = new ArrayList<Integer>();
            for(int j =0; j<n ; j++){
                a.add(g.get(i).get(j));
            }
            gg.add(a);
        }


        ArrayList<asdf> a = new ArrayList<asdf>();

        for(int i =0; i< n; i++) {
            asdf b = new asdf();
            a.add(b);
        }


        for(int i = 0; i< n; i++){
            //find pos
            for(int j = 0; j< n; j++){
                if(array.get(j) == i){
                    a.get(i).pos = j;
                    break;
                }
            }

            for(int j = 0; j<n; j++){
                if(gg.get(i).get(j) == 1){
                    for(int k = 0; k< n; k++){
                        if (array.get(k) == j){
                            a.get(i).idx.add(k);
                            gg.get(i).set(j, 0);
                            gg.get(j).set(i, 0);
                            break;
                        }
                    }
                }
            }
        }


        for (asdf it : a)
        {
            dist += it.allDist();
        }

        return dist;
    }


    public static void input(){
        try {
            //File inp = new File("/Users/gomsoup/Documents/algorithm_2019/audio/3.inp");
            File inp = new File("./audio.inp");
            Scanner scan = new Scanner(inp);

            n = scan.nextInt();
            for(int i =0; i<n; i++) {
                ArrayList<Integer> a = new ArrayList<Integer>();
                for(int j = 0; j< n; j++) a.add(0);
                g.add(a);
            }
            for(int i=0; i<n; i++){
                boolean flag = true;

                while(true){
                    int tmp; tmp = scan.nextInt();
                    if(flag == true){
                        flag = false; continue;
                    }

                    if(tmp == 0) break;
                    g.get(i).set(tmp - 1, 1);
                }
            }

        }
        catch(FileNotFoundException e) {
            System.out.println(e);
        }

    }


    public static ArrayList<Integer> nextPermute(ArrayList<Integer> nums) {
        ArrayList<Integer> copies = new ArrayList<Integer>();
        for(int i =0; i<n; i++) copies.add(0);
       // resize(copies, nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            copies.set(i,nums.get(i));
        }
        int idx = -1;
        for (int i = 0; i < copies.size() - 1; i++) {
            if (copies.get(i) < copies.get(i+1)) {
                idx = i;
            }
        }
        if (idx < 0) {
            //Last Permutation
            return null;
        }
        for (int i = copies.size() - 1; i > idx; i--) {
            if (copies.get(idx) < copies.get(i)) {
                int tmp = copies.get(idx);
                copies.set(idx, copies.get(i));
                copies.set(i, tmp);
                break;
            }
        }
        for (int i = idx + 1; i < (copies.size() + idx + 1) / 2; i++) {
            int tmp = copies.get(i);
            copies.set(i, copies.get(copies.size() - (i-idx)));
            copies.set(copies.size() - (i - idx),tmp);
        }

        return copies;
    }


    public static void forThread(int idx){
        ArrayList<Integer> v = new ArrayList<Integer>();
        for(int i =0; i<n; i++) v.add(0);
        int cnt = 1;
        for (int i = 0; i < n; i++)
        {
            if (i == idx)
            {
                continue;
            }
            v.set(cnt, i);
            cnt++;
        }
        v.set(0, idx);


        cnt = 0;
        do
        {
            if (v.get(0) != idx)
            {
                break;
            }
            int dist = calc(new ArrayList<Integer>(v));
    
            try {
                lock.lock();

                if (minDist >= dist) {
                    if (!result.isEmpty() && minDist == dist) {
                        for (int i = 0; i < n; i++) {
                            if (result.get(i) > v.get(i)) {
                                result.clear();
                                result = new ArrayList<Integer>();
                                for (int j = 0; j < n; j++)
                                    result.add(v.get(j));
                                break;
                            } else if (result.get(i) < v.get(i))
                                break;
                            else
                                continue;
                        }
                    } else {
                        result = new ArrayList<Integer>();
                        for (int i = 0; i < n; i++) result.add(v.get(i));
                        //result = result = (ArrayList<Integer>) v.clone();
                    }

                    //  result = (ArrayList<Integer>) v.clone();
                    minDist = dist;
                }
            }catch(Exception e){
                System.out.println(e);
            }
            finally{ lock.unlock(); }
            cnt++;
            v = nextPermute(v);
        }while (v != null);
    }

    public static void output() {
        try {
            File out = new File("./audio.out");
            BufferedWriter buf = new BufferedWriter(new FileWriter(out));

            buf.write(minDist + "\n");
            for(int i =0; i<n; i++) {
                int tmp = result.get(i) + 1;
                buf.write(tmp + " ");
            }
            buf.write("\n");
            buf.close();
        }catch(Exception e){
            System.out.println(e);
        }
    }

    public static void main(String[] args){
        input();

        ArrayList<Thread> list = new ArrayList<Thread>();
        for(int i =0; i<n; i++){
            final int tmp = i;
            list.add(new Thread(() -> forThread(tmp)));
        }
        for (int i = 0; i<n; i++){
            list.get(i).start();
        }
        for (int i = 0; i<n; i++){

            try{
                list.get(i).join();
            }catch(Exception e){
                System.out.println(e);
            }
        }

        output();
    }
}