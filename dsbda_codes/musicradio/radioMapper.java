package musicradio;

import java.io.IOException;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.Mapper;

public class radioMapper extends Mapper<LongWritable, Text, Text, Text> {
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        if (key.get() == 0 && value.toString().contains("UserId")) return; // skip header

        String[] fields = value.toString().split(",");
        if (fields.length < 5) return;
        String trackId = fields[1].trim();
        String radio = fields[3].trim();
        String skip = fields[4].trim();

        if (radio.equals("1")) {
            context.write(new Text(trackId), new Text("RADIO"));
        }
        if (skip.equals("1")) {
            context.write(new Text(trackId), new Text("SKIP"));
        }
    }
}