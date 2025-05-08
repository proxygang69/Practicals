package music;

import java.io.IOException;
import java.util.HashSet;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.Reducer;

public class MusicReducer extends Reducer<Text, Text, Text, Text> {
    public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
        HashSet<String> uniqueUsers = new HashSet<>();
        int shareCount = 0;
        for (Text val : values) {
            String v = val.toString();
            if (v.startsWith("USER:")) {
                uniqueUsers.add(v.substring(5));
            } else if (v.equals("SHARED")) {
                shareCount++;
            }
        }

        context.write(key, new Text("UniqueListeners: " + uniqueUsers.size() + ", SharedCount: " + shareCount));
    }
}
