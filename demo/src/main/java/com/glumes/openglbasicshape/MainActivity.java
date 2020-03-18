package com.glumes.openglbasicshape;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;

import com.glumes.databindingadapter.DataBindingAdapter;
import com.glumes.databindingadapter.Items;
import com.glumes.openglbasicshape.activitiy.BasicGraphActivity;
import com.glumes.openglbasicshape.activitiy.BasicShapeActivity;
import com.glumes.openglbasicshape.activitiy.TextureActivity;
import com.glumes.openglbasicshape.bezier.beziertouch.BezierTouchActivity;
import com.glumes.openglbasicshape.bezier.curve.BezierActivity;
import com.glumes.openglbasicshape.blend.BlendActivity;
import com.glumes.openglbasicshape.bufferusage.BufferUsageActivity;
import com.glumes.openglbasicshape.collision.CollisionActivity;
import com.glumes.openglbasicshape.egl.EglActivity;
import com.glumes.openglbasicshape.fbo.FrameBufferObjectActivity;
import com.glumes.openglbasicshape.filter.GLSurfaceViewFilterActivity;
import com.glumes.openglbasicshape.imageprocessing.ImageProcessingActivity;
import com.glumes.openglbasicshape.light.LightActivity;
import com.glumes.openglbasicshape.move.RotateAndMoveActivity;
import com.glumes.openglbasicshape.multitest.MultiTestActivity;
import com.glumes.openglbasicshape.obj.ImportObjectActivity;
import com.glumes.openglbasicshape.texturemix.TextureMixActivity;
import com.glumes.openglbasicshape.transition.TransitionActivity;
import com.glumes.openglbasicshape.transition_banner.TransitionBannerActivity;
import com.glumes.openglbasicshape.utils.RenderType;
import com.glumes.openglbasicshape.viewholderitem.RenderBinder;
import com.glumes.openglbasicshape.viewholderitem.RenderModel;
import com.glumes.video.FrameReplaceActivity;

import butterknife.BindView;
import butterknife.ButterKnife;

public class MainActivity extends AppCompatActivity {

    @BindView(R.id.rvRenderer)
    RecyclerView rvRenderer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_renderer);
        ButterKnife.bind(this);

        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        layoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        rvRenderer.setLayoutManager(layoutManager);

        Items items = new Items();

        DataBindingAdapter mAdapter = new DataBindingAdapter();
        mAdapter
                .map(RenderModel.class, new RenderBinder())
                .setItems(items);

        rvRenderer.setAdapter(mAdapter);


        items.add(new RenderModel("基本图形的绘制", RenderType.RENDER_TYPE_JUMP_ACTIVITY, BasicGraphActivity.class));

        items.add(new RenderModel("仿视频转场效果", RenderType.RENDER_TYPE_JUMP_ACTIVITY, TransitionActivity.class));

        items.add(new RenderModel("转场效果轮播图", RenderType.RENDER_TYPE_JUMP_ACTIVITY, TransitionBannerActivity.class));

        items.add(new RenderModel("贝塞尔曲线绘制",RenderType.RENDER_TYPE_JUMP_ACTIVITY, BezierActivity.class));

        items.add(new RenderModel("贝塞尔曲线手绘",RenderType.RENDER_TYPE_JUMP_ACTIVITY, BezierTouchActivity.class));

        items.add(new RenderModel("基本形状的绘制", RenderType.RENDER_TYPE_JUMP_ACTIVITY, BasicShapeActivity.class));

        items.add(new RenderModel("绘制纹理", RenderType.RENDER_TYPE_JUMP_ACTIVITY, TextureActivity.class));

        items.add(new RenderModel("旋转与移动篇", RenderType.RENDER_TYPE_JUMP_ACTIVITY, RotateAndMoveActivity.class));

        items.add(new RenderModel("FBO 使用", RenderType.RENDER_TYPE_JUMP_ACTIVITY, FrameBufferObjectActivity.class));

        items.add(new RenderModel("EGL 使用", RenderType.RENDER_TYPE_JUMP_ACTIVITY, EglActivity.class));

        items.add(new RenderModel("相机滤镜", RenderType.RENDER_TYPE_JUMP_ACTIVITY, GLSurfaceViewFilterActivity.class));

        items.add(new RenderModel("着色器图像处理", RenderType.RENDER_TYPE_JUMP_ACTIVITY, ImageProcessingActivity.class));

        items.add(new RenderModel("裁剪与测试", RenderType.RENDER_TYPE_JUMP_ACTIVITY, MultiTestActivity.class));

        items.add(new RenderModel("3D 模型导入", RenderType.RENDER_TYPE_JUMP_ACTIVITY, ImportObjectActivity.class));

        items.add(new RenderModel("光照", RenderType.RENDER_TYPE_JUMP_ACTIVITY, LightActivity.class));

        items.add(new RenderModel("相机录制", RenderType.RENDER_TYPE_JUMP_ACTIVITY, CameraRawDataCodecActivity.class));

        items.add(new RenderModel("混合与纹理压缩", RenderType.RENDER_TYPE_JUMP_ACTIVITY, BlendActivity.class));

        items.add(new RenderModel("视频帧处理", RenderType.RENDER_TYPE_JUMP_ACTIVITY, FrameReplaceActivity.class));

        items.add(new RenderModel("缓冲区的使用", RenderType.RENDER_TYPE_JUMP_ACTIVITY, BufferUsageActivity.class));

        items.add(new RenderModel("碰撞检测", RenderType.RENDER_TYPE_JUMP_ACTIVITY, CollisionActivity.class));

        items.add(new RenderModel("纹理混合", RenderType.RENDER_TYPE_JUMP_ACTIVITY, TextureMixActivity.class));


    }


}
