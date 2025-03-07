/**
 * @file Product.h
 * @author Attulya Pratap Gupta
 *
 *
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include "Item.h"
#include "Level.h"
#include <map>

#include "Conveyor.h"

/**
 * Class to represent a product on the conveyor
 */
class Product : public Item
{
private:
	/// The possible product properties
	enum class Properties
	{
		None, Red, Green, Blue, White, Square, Circle, Diamond,
		Izzo, Smith, Football, Basketball
	};

	/// The property types
	enum class Types { Color, Shape, Content };

	/// The color of the product
	Properties mColor = Properties::None;

	/// The shape of the product
	Properties mShape = Properties::None;

	/// The content of the product
	Properties mContent = Properties::None;

	/// Whether this product should be kicked
	bool mShouldKick = false;

	/// Whether the product is already kicked
	bool mKicked = false;

    /// Whether or not the product is currently being detected
    bool mDetected = false;

	/// Previous detection state
	bool mWasDetected = false;

	/// Whether or not the product has left the beam
	bool mPassedBeam = false;

	/// Whether or not the product has been scored;
	bool mScored = false;

	/// The placement of the product on the conveyor
	double mPlacement = 0;

	/// The speed at which the product is moving (for kicking)
	double mSpeed = 0;

	/// The initial x placement of the product
	double mInitialX;
	/// The initial y placement of the product
	double mInitialY;

	/// The kick speed of the product
	double mKickSpeed = 0;

	/// The image for the contents of the product
	std::unique_ptr<wxImage> mContentImage;

	/// The bitmap for the contents of the product
	std::unique_ptr<wxBitmap> mContentBitmap;

public:
	Product(Level *level);

	/**
	 * @brief Destructor for Product
	 */
	virtual ~Product();


	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	void XmlLoad(wxXmlNode *node) override;

	void Update(double elapsed) override;

	/**
	 *  Getter for product color
	 *  @return Properties color
	 * */
	Properties GetColor() const { return mColor; }

	/**
	 *  Getter for product shape
	 *  @return Properties shape
	 * */
	Properties GetShape() const { return mShape; }

	/**
	 *  Getter for product content
	 *  @return Properties content
	 * */
	Properties GetContent() const { return mContent; }

	/**
	*  Getter for product kick state
	*  @return bool whether or not the product should be kicked
	* */
	bool ShouldKick() const { return mShouldKick; }

	/**
   *  Getter for product placement
   *  @return double placement of the product
   * */
	double GetPlacement() const { return mPlacement; }

	/**
	 * Getter for product kicked state
	 * @return bool whether product has been kicked
	 */
	bool GetKicked() const { return mKicked; }

    /**
	 * Getter for product detected state
	 * @return bool whether product has been detected
	 */
    bool GetDetected() const { return mDetected; }

	/**
	 * Getter for product scored state
	 * @return bool whether product has been scored
	 */
	bool GetScored() const { return mScored; }

	/**
	 * Setter for if product is kicked
	 * @param kickState whether product is kicked
	 */
	void SetKicked(bool kickState) { mKicked = kickState; }

	/**
	 * Setter for kick speed of product
	 * @param speed speed of the kick
	 */
	void SetKickSpeed(double speed) { mKickSpeed = speed; }

	/**
	 * Setter for scored state of product
	 * @param scored scored state of product
	 */
	void SetScored(bool scored) { mScored = scored; }

	void SetDetected(bool detected);

	/// Mapping from the XML strings for properties to the Properties enum
	static const std::map<std::wstring, Properties> NamesToProperties;

	/// Mapping from a property to its type
	static const std::map<Properties, Types> PropertiesToTypes;

	/// Mapping from content properties to their associated image
	static const std::map<Properties, std::wstring> PropertiesToContentImages;

	void Accept(VisitorBase *visitor) override;


	/**
	 * @brief Set the initial position of the product
	 * @param conveyorX The X coordinate of the conveyor
	 * @param conveyorY The Y coordinate of the conveyor
	 * @param conveyorHeight The height of the conveyor
	 */
	void SetInitialPosition(double conveyorX, double conveyorY, double conveyorHeight);

	/**
	 * @brief Reset the product to its initial position
	 * @param conveyor Pointer to the Conveyor object
	 */
	void Reset(Conveyor *conveyor);

	void Move(double elapsed, double speed);

	std::tuple<double, double> GetYRange();

	/**
	 * Check if this product has passed the beam
	 * @return True if the product has passed the beam
	 */
	bool GetPassedBeam() const { return mPassedBeam; }

};

#endif // PRODUCT_H
