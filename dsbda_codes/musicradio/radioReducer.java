package musicradio;

import java.io.IOException;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.Reducer;

public class radioReducer extends Reducer<Text, Text, Text, Text> {
    public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
        int radioCount = 0;
        int skipCount = 0;

        for (Text val : values) {
            if (val.toString().equals("RADIO")) {
                radioCount++;
            } else if (val.toString().equals("SKIP")) {
                skipCount++;
            }
        }

        context.write(key, new Text("RadioCount: " + radioCount + ", SkipCount: " + skipCount));
    }
}