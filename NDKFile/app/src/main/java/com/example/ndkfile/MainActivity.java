package com.example.ndkfile;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView text;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initUi();


        // Example of a call to a native method
        TextView tv = findViewById(R.id.text);

    }

    private void initUi() {
        findViewById(R.id.btn_s0).setOnClickListener(this);
        findViewById(R.id.btn_s1).setOnClickListener(this);
        findViewById(R.id.btn_s2).setOnClickListener(this);
        text = findViewById(R.id.text);


        stringFromJNI("/data/data/");


    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void stringFromJNI(String dirPath);


    private static ArrayList<String> executeCommand(String[] shellCmd) {
        String line = null;
        ArrayList<String> result = new ArrayList<String>();
        Process localProcess = null;
        try {
            localProcess = Runtime.getRuntime().exec(shellCmd);
        } catch (IOException e) {
            return null;
        }
        BufferedReader in = new BufferedReader(new InputStreamReader(localProcess.getInputStream()));
        try {
            while ((line = in.readLine()) != null) {
                result.add(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (in != null)
                    in.close();
                if (localProcess != null)
                    localProcess.destroy();
            } catch (IOException e) {

            }
        }
        return result;
    }


    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_s0:
                exextionSu();
                break;
            case R.id.btn_s1:
                stringFromJNI("/data/data/");
                break;
            case R.id.btn_s2:
                //testShell2();
                //shellExec();
                text.setText(execCommand(shell, true));
                break;

        }
    }

    //雷电
    public static final String LEIDIAN = "com.android.flysilkworm";

    //夜神
    public static final String NOX = "com.bignox";


    //逍遥
    public static final String XIAOYAO = "com.microvirt";


    //木木
    public static final String MUMU =
            "";
    //蓝蝶
    public static final String BLUESTACK = "";


    public static final String COMMAND_SU = "su";
    public static final String COMMAND_SH = "sh";
    public static final String COMMAND_EXIT = "exit\n";
    public static final String COMMAND_LINE_END = "\n";

    public static String execCommand(String[] commands, boolean isRoot) {
        int result = -1;
        if (commands == null || commands.length == 0) {
            return "";
        }

        Process process = null;
        BufferedReader successResult = null;
        BufferedReader errorResult = null;
        StringBuilder successMsg = null;


        DataOutputStream os = null;
        try {
            process = Runtime.getRuntime().exec(isRoot ? COMMAND_SU : COMMAND_SH);
            os = new DataOutputStream(process.getOutputStream());
            for (String command : commands) {
                if (command == null) {
                    continue;
                }

                os.write(command.getBytes());
                os.writeBytes(COMMAND_LINE_END);
                os.flush();
            }
            os.writeBytes(COMMAND_EXIT);
            os.flush();
            result = process.waitFor();

            successMsg = new StringBuilder();
            successResult = new BufferedReader(new InputStreamReader(
                    process.getInputStream()));
            String s;
            while ((s = successResult.readLine()) != null) {
                successMsg.append(s);
            }
            return successMsg.toString();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (os != null) {
                    os.close();
                }
                if (successResult != null) {
                    successResult.close();
                }
                if (errorResult != null) {
                    errorResult.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            if (process != null) {
                process.destroy();
            }
        }
        return successMsg.toString();
    }


    private void testShell2() {
        ShellUtils.CommandResult commandResult = ShellUtils.execCommand("ls /data/data/", false);
        //text.setText(commandResult.errorMsg);
        text.setText(commandResult.successMsg);

    }


    String shell[] = {"ls /data/data/"};

    //String shell[] = {"/system/bin/ls",   "/mnt/sdcard/"};
    private void testShell() {
        ArrayList<String> strings = executeCommand(shell);
        if (null == strings || strings.size() == 0) {
            text.setText("没拿到包名");
            return;
        }
        for (int i = 0; i < strings.size(); i++) {
            text.append("\r\n");
            text.append(strings.get(i));
        }
    }


    private static synchronized boolean exextionSu() {
        Process suProcess = null;
        DataOutputStream os = null;
        try {
            suProcess = Runtime.getRuntime().exec("su");
            os = new DataOutputStream(suProcess.getOutputStream());
            os.writeBytes("exit\n");
            os.flush();
            int exitValue = suProcess.waitFor();
            if (exitValue == 0) {
                return true;
            }
        } catch (Exception e) {
            return false;
        } finally {
            try {
                if (os != null) {
                    os.close();
                }
                if (suProcess != null) {
                    suProcess.destroy();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return false;
    }

    public void shellExec() {
        Runtime mRuntime = Runtime.getRuntime();
        try {
            //Process中封装了返回的结果和执行错误的结果
            Process mProcess = mRuntime.exec("ls /data/data/");
            BufferedReader mReader = new BufferedReader(new InputStreamReader(mProcess.getInputStream()));
            StringBuffer mRespBuff = new StringBuffer();
            char[] buff = new char[1024];
            int ch = 0;
            while ((ch = mReader.read(buff)) != -1) {
                mRespBuff.append(buff, 0, ch);
            }
            mReader.close();
            //System.out.print(mRespBuff.toString());
            text.setText(mRespBuff.toString());
        } catch (IOException e) {
            // TODO Auto-generated catch block
            text.setText(e.getLocalizedMessage());
            e.printStackTrace();
        }
    }

}
