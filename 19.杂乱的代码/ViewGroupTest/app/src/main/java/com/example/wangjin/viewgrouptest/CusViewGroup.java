package com.example.wangjin.viewgrouptest;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;

public class CusViewGroup extends ViewGroup {
    private final String TAG = this.getClass().getSimpleName();

    public CusViewGroup(Context context) {
        super(context);
    }

    public CusViewGroup(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public CusViewGroup(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }


    /**
     * 计算所有ChildView的宽度和高度，然后根据ChildView的计算结果，设置自己的宽高
     */
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        /**
         * 获得当前ViewGroup上级容器推荐的宽高以及计算模式
         */
        int widthMode = MeasureSpec.getMode(widthMeasureSpec);
        int heightMode = MeasureSpec.getMode(heightMeasureSpec);
        int sizeWidth = MeasureSpec.getSize(widthMeasureSpec);
        int sizeHeight = MeasureSpec.getSize(heightMeasureSpec);

        Log.e(TAG, (heightMode == MeasureSpec.UNSPECIFIED) + "," + sizeHeight
                + "," + getLayoutParams().height);

        // 璁＄畻鍑烘墍鏈夌殑childView鐨勫鍜岄珮
        measureChildren(widthMeasureSpec, heightMeasureSpec);
        /**
         * 定义宽高变量
         */
        int width = 0;
        int height = 0;

        // 获得子View的数量
        int cCount = getChildCount();

        int cWidth = 0;
        int cHeight = 0;
        //定义Margin布局参数
        MarginLayoutParams cParams = null;

        int lHeight = 0;
        int rHeight = 0;
        int tWidth = 0;
        int bWidth = 0;

        /**
         * 遍历所有子View，获得所有子View的宽高，及Margin信息，主要用于子View为wrap_content时
         */
        for (int i = 0; i < cCount; i++) {
            View childView = getChildAt(i);//获取子View
            cWidth = childView.getMeasuredWidth();
            cHeight = childView.getMeasuredHeight();
            cParams = (MarginLayoutParams) childView.getLayoutParams();

            // 涓婇潰涓や釜childView
            if (i == 0 || i == 1) {
                tWidth += cWidth + cParams.leftMargin + cParams.rightMargin;
            }

            if (i == 2 || i == 3) {
                bWidth += cWidth + cParams.leftMargin + cParams.rightMargin;
            }

            if (i == 0 || i == 2) {
                lHeight += cHeight + cParams.topMargin + cParams.bottomMargin;
            }

            if (i == 1 || i == 3) {
                rHeight += cHeight + cParams.topMargin + cParams.bottomMargin;
            }

        }

        width = Math.max(tWidth, bWidth);
        height = Math.max(lHeight, rHeight);

        /**
         * 判断测量模式
         */
        setMeasuredDimension((widthMode == MeasureSpec.EXACTLY) ? sizeWidth
                : width, (heightMode == MeasureSpec.EXACTLY) ? sizeHeight
                : height);
    }

    // abstract method in viewgroup
    @Override
    protected void onLayout(boolean changed, int l, int t, int r, int b) {
        int cCount = getChildCount();
        int cWidth = 0;
        int cHeight = 0;
        MarginLayoutParams cParams = null;
        /**
         * 遍历所有childView根据其宽和高，以及margin进行布局
         */
        for (int i = 0; i < cCount; i++) {
            View childView = getChildAt(i);
            cWidth = childView.getMeasuredWidth();
            cHeight = childView.getMeasuredHeight();
            cParams = (MarginLayoutParams) childView.getLayoutParams();

            int cl = 0, ct = 0, cr = 0, cb = 0;

            switch (i) {
                case 0:
                    cl = cParams.leftMargin;
                    ct = cParams.topMargin;
                    break;
                case 1:
                    cl = getWidth() - cWidth - cParams.leftMargin
                            - cParams.rightMargin;
                    ct = cParams.topMargin;

                    break;
                case 2:
                    cl = cParams.leftMargin;
                    ct = getHeight() - cHeight - cParams.bottomMargin;
                    break;
                case 3:
                    cl = getWidth() - cWidth - cParams.leftMargin
                            - cParams.rightMargin;
                    ct = getHeight() - cHeight - cParams.bottomMargin;
                    break;

            }
            cr = cl + cWidth;
            cb = cHeight + ct;
            childView.layout(cl, ct, cr, cb);
        }

    }

    @Override
    public ViewGroup.LayoutParams generateLayoutParams(AttributeSet attrs) {
        Log.e(TAG, "generateLayoutParams");
        //获取对应XML中的属性个数
        attrs.getAttributeCount();
        for(int i = 0; i < attrs.getAttributeCount(); i++){
            Log.e(TAG, attrs.getAttributeName(i) + " = "  + "namespace = " + attrs.getAttributeNameResource(i));
        }

        Log.e(TAG, "--------------");
        return new MarginLayoutParams(getContext(), attrs);
    }

    @Override
    protected ViewGroup.LayoutParams generateDefaultLayoutParams() {
        Log.e(TAG, "generateDefaultLayoutParams");
        return new MarginLayoutParams(LayoutParams.MATCH_PARENT,
                LayoutParams.MATCH_PARENT);
    }

    @Override
    protected ViewGroup.LayoutParams generateLayoutParams(
            ViewGroup.LayoutParams p) {
        Log.e(TAG, "generateLayoutParams p");
        return new MarginLayoutParams(p);
    }


    @Override
    protected void onFinishInflate() {
        Log.e(TAG, "onFinishInflate...");
        super.onFinishInflate();
    }
}
