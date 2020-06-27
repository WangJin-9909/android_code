package com.wangjin.recyclerviewtest;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.ListAdapter;
import androidx.recyclerview.widget.RecyclerView;
import butterknife.BindView;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.ViewGroup;

public class MainActivity extends AppCompatActivity {
    @BindView(R.id.recyclerview)
    RecyclerView mRecyclerView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initView();
        initData();

    }

    private void initData() {



    }

    private void initView() {
        setContentView(R.layout.activity_main);

    }







    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        return super.onCreateOptionsMenu(menu);
    }


    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        int itemId = item.getItemId();
        switch (itemId) {
            //LisetView
            case R.id.list_view_vertical_stander:
                break;
            case R.id.list_view_vertical_reserve:
                break;
            case R.id.list_view_horizional_stander:
                break;
            case R.id.list_view_horizional_reserve:
                break;


            //GirdView
            case R.id.gird_view_vertical_stander:
                break;
            case R.id.gird_view_vertical_reserve:
                break;
            case R.id.gird_view_horizional_stander:
                break;
            case R.id.gird_view_horizional_reserve:
                break;
            //瀑布流
            case R.id.stagger_view_vertical_stander:
                break;
            case R.id.stagger_view_vertical_reserve:
                break;
            case R.id.stagger_view_horizional_stander:
                break;
            case R.id.stagger_view_horizional_reserve:
                break;


        }


        return super.onOptionsItemSelected(item);
    }
}
