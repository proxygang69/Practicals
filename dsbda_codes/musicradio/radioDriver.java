package musicradio;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class radioDriver {
    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "Radio and Skip Counter");
        job.setJarByClass(radioDriver.class);
        job.setMapperClass(radioMapper.class);
        job.setReducerClass(radioReducer.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);

        FileInputFormat.addInputPath(job, new Path(args[0])); // HDFS input file
        FileOutputFormat.setOutputPath(job, new Path(args[1])); // HDFS output dir
        job.setJarByClass(radioDriver.class);
        job.setMapperClass(radioMapper.class);
        job.setReducerClass(radioReducer.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);

        FileInputFormat.addInputPath(job, new Path(args[0])); // HDFS input file
        FileOutputFormat.setOutputPath(job, new Path(args[1])); // HDFS output dir
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}