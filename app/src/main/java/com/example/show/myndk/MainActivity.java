package com.example.show.myndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import java.nio.ByteBuffer;



public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        TextView intTV = (TextView) findViewById(R.id.textView1);
        int value = intFromJNI();
        intTV.setText(String.valueOf(value));

        TextView intTV2 = (TextView) findViewById(R.id.textView2);
        int[] arr = {1,2,3,4,5};
        intTV2.setText(strArray(arr));

        getArrayFromJNI(arr);
        getStringArrayFromJNI();

        fromJNICallJavaMethod();
    }

    public void getArrayFromJNI(int[] arr) {
        TextView intTV = (TextView) findViewById(R.id.textView3);
        int[] res = getArray(arr);
        intTV.setText(java.util.Arrays.toString(res));

        TextView intTV1 = (TextView) findViewById(R.id.textView4);
        intTV1.setText(java.util.Arrays.toString(arr));

    }

    public void getStringArrayFromJNI() {
        TextView tv = findViewById(R.id.textView5);
//        String[] str = getStringArray();
        tv.setText(java.util.Arrays.toString(getStringArray()));
//        System.out.print(str[0]);
    }

    public void fromJNICallJavaMethod() {
        Zoo zoo = createZoo("CA", 5);
        System.out.println(printData(zoo));
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int intFromJNI();
    public native String strArray(int[] arr);
    public native int[] getArray(int[] arr);

    public native int sendStream(ByteBuffer in);
    public native String[] getStringArray();

    //for Eddie
    public native Zoo createZoo(String name, int size);
    public native String printData(Zoo zoo);
}
