#ifndef _GCTP_GRAPHIC_SHADER_HPP_
#define _GCTP_GRAPHIC_SHADER_HPP_
/** @file
 * GameCatapult シェーダークラスヘッダファイル
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/01/28 12:43:53
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include <gctp/graphic.hpp>
#include <gctp/graphic/rsrc.hpp>
#include <gctp/class.hpp>

namespace gctp {
	class Skeleton;
}

namespace gctp { namespace graphic {

	// やっぱりBrushに戻したいなぁ。
	//!!
	// シェーダーとブラッシュは分けなきゃだめ。
	// Brushにおしゃれな名前以外の意義が出てきた。
	// Shader＝シェーダそのもの。
	// Brush=モデルごとのインスタンスデータ。
	// いまのModelDetail=Brush

	class Model;

	/// シェーダーリソースクラス
	class Shader : public Rsrc {
	public:
		virtual HRslt setUp(const _TCHAR *fname) = 0;

		/// 指定のテクニックがあるか？
		virtual bool hasTechnique(const char *name) const = 0;
		/// 適用開始
		virtual HRslt begin() const = 0;
		/// 適用終了
		virtual HRslt end() const = 0;
		/// 指定のパスを適用開始
		virtual HRslt beginPass(uint passno) const = 0;
		/// 指定のパスを適用終了
		virtual HRslt endPass() const = 0;
		/// パス数を返す（begin~endの間のみ有効）
		virtual uint passnum() const = 0;

#if 0
		// こいつらいらないかも
		// どこに何を入れるか、はBrushがしってる、ってことでいいんじゃ？

		/** モデルインスタンスごとではない、パラメータの設定
		 *
		 * ViewProjectionMatrixやアンビエントなど
		 *
		 * begin前に設定可能なパラメータ
		 */
		virtual void setGlobalParameter() = 0;
		/** モデルインスタンスごとのパラメータの設定
		 *
		 * ModelMatrix（WorldMatrix）や動的ライトなど
		 *
		 * 描画直前に設定するパラメータ
		 */
		virtual void setLocalParameter(const Model &model, int subsetno, const Matrix &mat) = 0;
		/** モデルインスタンスごとのパラメータの設定
		 *
		 * ModelMatrix（WorldMatrix）や動的ライトなど
		 *
		 * 描画直前に設定するパラメータ
		 */
		virtual void setLocalParameter(const Model &model, int subsetno, const Skeleton &skel) = 0;
#endif

		// とりあえず。。。
		// NULLにすると先頭のテクニックで描画
		static void setTechnique(const char *techname)
		{
			current_technique_ = techname;
		}

		static const char *getTechnique()
		{
			return current_technique_;
		}

	protected:
		static const char *current_technique_;
		// これはレンダーツリーが持つべき

	GCTP_DECLARE_TYPEINFO
	};

}} //namespace gctp

#endif // _GCTP_GRAPHIC_SHADER_HPP_