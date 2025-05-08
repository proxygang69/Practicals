package logfile;
import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;


public class LogReducer extends Reducer<Text, IntWritable, Text, IntWritable>{
	@Override
	public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException{
		int totalTime = 0;
		for(IntWritable value : values){
			totalTime += value.get();
		}
		context.write(key, new IntWritable(totalTime));
	}
}
