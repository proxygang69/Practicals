package logfile;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;


public class LogMapper extends Mapper<LongWritable, Text, Text, IntWritable>{
	public SimpleDateFormat format = new SimpleDateFormat("M/d/yyyy H:mm");
	
	@Override
	public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException{
		String[] fields = value.toString().split(",");
		try{	
			if(fields.length == 8){
				String user = fields[1].toString();
				Date login = format.parse(fields[5]);
				Date logout = format.parse(fields[7]);
				
				long time = (logout.getTime() - login.getTime())/(60*1000);
				
				if(time >= 0){				
					context.write(new Text(user), new IntWritable((int)time));
				}
			}
		} catch (Exception e){
			// skip row
		}
	}
}
