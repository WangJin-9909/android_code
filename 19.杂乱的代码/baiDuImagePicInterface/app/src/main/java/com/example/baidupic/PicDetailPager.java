package com.example.baidupic;

import com.nostra13.universalimageloader.core.DisplayImageOptions;
import com.nostra13.universalimageloader.core.ImageLoader;

import android.app.Activity;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.Window;
import android.widget.ImageView;

public class PicDetailPager extends Activity {
	private ImageView detial_pic;
	private ImageLoader loader;
	private DisplayImageOptions options;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		initData();
		initUI();
	}

	private void initUI() {
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_detail);
		detial_pic = (ImageView) findViewById(R.id.detial_iv);

		loader.displayImage(getIntent().getStringExtra("url"), detial_pic,
				options);

	}

	private void initData() {
		loader = ImageLoader.getInstance();
		options = new DisplayImageOptions.Builder()
				.showImageOnLoading(R.drawable.ic_launcher)
				// 正在加载
				.showImageForEmptyUri(R.drawable.ic_launcher)
				// 空图片
				.showImageOnFail(R.drawable.ic_launcher)
				// 错误图片
				.cacheInMemory(true).cacheOnDisk(true).considerExifParams(true)
				.bitmapConfig(Bitmap.Config.RGB_565).build();
	}

	@Override
	public void onBackPressed() {
		// TODO Auto-generated method stub
		super.onBackPressed();
		finish();
	}
}
