import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class papersnowflakes_da {

    static class Event implements Comparable<Event> {
        long x;
        int t;

        Event(long x, int t) {
            this.x = x;
            this.t = t;
        }

        @Override
        public int compareTo(Event o) {
            int comp = Long.compare(x, o.x);
            if (comp == 0) comp = Integer.compare(t, o.t);
            return comp;
        }

        public String toString() {
            return String.format("{%d, %d}", x, t);
        }
    }

    private static final long INF = 1L << 62;

    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int n = sc.nextInt();
        int m = sc.nextInt();
        long l = sc.nextLong();

        List<Event> events = new ArrayList<>();
        events.add(new Event(0, -2));
        int t = 1;
        long left = 0;
        long right = l;
        while (n-- > 0) {
            long x = sc.nextLong();
            if (t == 1) {
                left = right - 2 * x;
                right -= x;
                events.add(new Event(right, 1));
            } else {
                right = left + 2 * x;
                left += x;
                events.add(new Event(left, 0));
            }

            t = 1 - t;
        }

        if (t == 0) {
            events.add(new Event(left, -2));
        } else {
            events.add(new Event(right, -1));
        }

        while (m-- > 0) {
            events.add(new Event(sc.nextLong(), 2));
        }

        Collections.sort(events);
        // System.err.println(events);

        long total = 0;
        int cnt = 0;
        long prev = Long.MIN_VALUE;
        long rem = l;
        for (Event e : events) {
            if (prev > Long.MIN_VALUE) {
                total += cnt * (e.x - prev);
            }

            switch (e.t) {
                case -2: // loose start
                    cnt++;
                    break;
                case -1: // loose end
                    cnt--;
                    break;
                case 0: // start
                    cnt += 2;
                    break;
                case 1: // end
                    cnt -= 2;
                    break;
                case 2: // cut
                    System.out.printf("%d ", total);
                    rem -= total;
                    total = 0;
                    break;
            }

            prev = e.x;
        }

        System.out.println(rem);
    }

    public static void main(String[] args) {
        new papersnowflakes_da().work();
    }
}
