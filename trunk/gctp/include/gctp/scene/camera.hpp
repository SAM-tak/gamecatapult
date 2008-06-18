#ifndef _GCTP_SCENE_CAMERA_HPP_
#define _GCTP_SCENE_CAMERA_HPP_
/** @file
 * GameCatapult カメラクラスヘッダファイル
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/02/08 11:18:38
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include <gctp/class.hpp>
#include <gctp/types.hpp>
#include <gctp/strutumnode.hpp>
#include <gctp/frustum.hpp>
#include <gctp/tuki.hpp>
#include <gctp/scene/renderer.hpp>

namespace gctp { namespace scene {

	/** カメラ
	 *
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/02/16 8:10:04
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	class Camera : public Renderer
	{
	public:
		/// コンストラクタ
		Camera();

		virtual bool onReach(float delta) const;
		virtual bool onLeave(float delta) const;

		/// カメラ位置設定
		void setStance(Stance &src);
		/// 階層ノードにアタッチ
		void attach(Handle<StrutumNode> node);

		/// カメラ位置
		const Stance &stance() const { return stance_; }
		/// ニアクリップ
		const float &nearclip() const { return nearclip_; }
		/// ニアクリップ
		float &nearclip() { return nearclip_; }
		/// ファークリップ
		const float &farclip() const { return farclip_; }
		/// ファークリップ
		float &farclip() { return farclip_; }
		/// 視野角
		const float &fov() const { return fov_; }
		/// 視野角
		float &fov() { return fov_; }
		/// サブウィンドウ
		const Rectf &subwindow() const { return subwindow_; }
		/// サブウィンドウ
		Rectf &subwindow() { return subwindow_; }
		/// アタッチしているノードを返す
		Handle<StrutumNode> node() const { return node_; }
		/// 独自にウィンドウサイズを指定
		void setWindow(float w, float h)
		{
			window_.x = w;
			window_.y = h;
		}
		/// 現在のスクリーンからアスペクトを設定(デフォルト)
		void fitToScreen() { window_.x = 0; }
		/// 投影サイズがレンダーターゲットと一致しているか？
		bool isFittedToScreen() const { return window_.x == 0 || window_.y == 0; }
		/// 投影モードか？
		bool isPerspective() const { return fov_ > 0; }

		/// ヴューマトリクスを返す
		Matrix view() const;
		/// 投影マトリクスを返す
		Matrix projection() const;
		/// 投影スクリーンサイズを返す
		Size2f screen() const;

		const Matrix &viewprojection() const { return viewprojection_; }

		/// カメラをグラフィックシステムに設定
		void setToSystem() const;
		/// カメラ設定開始
		void begin() const;
		/// カメラ設定終了
		void end() const;

		/// カレントカメラ（このカメラの子レンダリング要素にのみ有効）		
		static Camera &current() { return *current_; }

		/// ヴューフラスタム内か判定
		bool isVisible(const Sphere &bs) const
		{
			return frustum_.isColliding(bs);
		}

		/// 視錘台
		const Frustum &frustum() { return frustum_; }

		/// 視錘台を更新
		void update();

	protected:
		bool setUp(luapp::Stack &L);
		void activate(luapp::Stack &L);
		void setPosition(luapp::Stack &L);
		int getPosition(luapp::Stack &L);
		void setPosture(luapp::Stack &L);
		int getPosture(luapp::Stack &L);
		void setDirection(luapp::Stack &L);
		int getDirection(luapp::Stack &L);
		void setClip(luapp::Stack &L);
		int getClip(luapp::Stack &L);
		void setFov(luapp::Stack &L);
		int getFov(luapp::Stack &L);

	private:
		Stance stance_;
		float nearclip_;
		float farclip_;
		float fov_;
		Size2f window_;
		Rectf subwindow_;
		Frustum frustum_;
		mutable Matrix viewprojection_;

		Handle<StrutumNode> node_;

		mutable Camera* backup_current_;
		GCTP_TLS static Camera* current_;

	GCTP_DECLARE_CLASS
	TUKI_DECLARE(Camera)
	};

}} // namespace gctp::scene

#endif //_GCTP_SCENE_CAMERA_HPP_