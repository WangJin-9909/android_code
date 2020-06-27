package com.example.baidupic;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.alibaba.fastjson.JSON;
import com.example.baidupic.bean.ImageData;
import com.example.baidupicn.net.HttpUtils;

import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;


/**
 * @author WangJin
 * @date 20170813
 * @function 目前的功能实现了，点击获取图片按钮就会在Wifi环境下获取百度的图片，与百度服务器之间通过JSON交接数据，然后并创建LIstView显示在LIstView上面
 * 并且为ListView设置了按下监听事件，当用户按下某个条目的时候就会进入一个详情页面显示大图
 */

public class MainActivity extends Activity {

    private Button bt_get;
    private TextView tv_pic;
    private JSONObject mJsonObject;
    private List<ImageData> data = new ArrayList<ImageData>();
    private String Content = "";
    private String url = "" + "&" + "";
    private JSONArray mJsonArray;
    private ListView lv_pic;
    private Handler mHandler = new Handler() {
        public void handleMessage(android.os.Message msg) {
            tv_pic.setText(data.size() + "长度");
            lv_pic.setAdapter(new PicAdapter());
            adapter.notifyDataSetChanged();
        }

        ;

    };
    private PicAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt_get = (Button) findViewById(R.id.getpic);
        tv_pic = (TextView) findViewById(R.id.tv_pic);
        lv_pic = (ListView) findViewById(R.id.lv_pic);


        adapter = new PicAdapter();
        lv_pic.setAdapter(adapter);
        lv_pic.setOnItemClickListener(new OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> arg0, View arg1, int position,
                                    long arg3) {
                // TODO Auto-generated method stub
                Intent intent = new Intent(MainActivity.this,
                        PicDetailPager.class);
                intent.putExtra("url", data.get(position).getDownload_url());
                startActivity(intent);
            }

        });

        bt_get.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                // 开启下载数据线程
                new Download().start();
            }
        });
    }

    /**
     * ?????????
     *
     * @author WangJin
     */
    class Download extends Thread {
        @Override
        public void run() {
            // TODO Auto-generated method stub
            super.run();
            try {

                Content = HttpUtils.getContent(url);
                Log.e("wangJin", Content.toString());
                mJsonObject = new JSONObject(Content);

                mJsonArray = mJsonObject.getJSONArray("data");
                Log.i("Test", "mJsonArray = " + mJsonArray);
                ImageData imageData = null;
                for (int k = 0; k < mJsonArray.length(); k++) {
                    JSONObject objs = mJsonArray.getJSONObject(k);
                    imageData = JSON.parseObject(objs.toString(),
                            ImageData.class);
                    data.add(imageData);
                    Log.i("Test",
                            "GET DATA, imageData = "
                                    + imageData.getDownload_url());
                    sleep(300);
                   mHandler.sendEmptyMessage(0);

                }
            } catch (JSONException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            } catch (Exception e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    class PicAdapter extends BaseAdapter {

        @Override
        public int getCount() {
            // TODO Auto-generated method stub
            return data.size();
        }

        @Override
        public Object getItem(int position) {
            // TODO Auto-generated method stub
            return data.get(position);
        }

        @Override
        public long getItemId(int position) {
            // TODO Auto-generated method stub
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            // TODO Auto-generated method stub
            View view = View.inflate(MainActivity.this, R.layout.item, null);
            TextView tv = (TextView) view.findViewById(R.id.url);
            tv.setText(data.get(position).getDownload_url());

            return view;
        }

    }


}
