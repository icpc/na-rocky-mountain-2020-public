import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class distance_da {

    static class Point implements Comparable<Point> {
        long x, cnt, totLeft, totRight;

        Point(long x, int cnt) {
            this.x = x;
            this.cnt = cnt;
        }

        @Override
        public int compareTo(Point o) {
            return Long.compare(x, o.x);
        }
    }

    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int n = sc.nextInt();
        long[] x = new long[n];
        long[] y = new long[n];
        for (int i = 0; i < n; i++) {
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();
        }

        System.out.println(solve(x) + solve(y));
    }

    private long solve(long[] a) {
        TreeMap<Long, Integer> ps = new TreeMap<>();
        for (long x : a) {
            if (!ps.containsKey(x)) ps.put(x, 0);
            ps.put(x, ps.get(x) + 1);
        }

        Point[] p = new Point[ps.size()];
        int k = 0;
        for (Map.Entry<Long, Integer> e : ps.entrySet()) {
            p[k++] = new Point(e.getKey(), e.getValue());
        }
        p[0].totLeft = p[0].cnt;
        for (int i = 1; i < p.length; i++) p[i].totLeft = p[i].cnt + p[i - 1].totLeft;

        p[p.length - 1].totRight = p[p.length - 1].cnt;
        for (int i = p.length - 2; i >= 0; i--) p[i].totRight = p[i].cnt + p[i + 1].totRight;

        long ret = 0;
        for (int i = 0; i < p.length - 1; i++) {
            long len = p[i + 1].x - p[i].x;
            ret += len * p[i].totLeft * p[i + 1].totRight;
        }

        return ret;
    }

    public static void main(String[] args) {
        new distance_da().work();
    }
}
