using UnityEngine;

public interface IConvexRegion
{
    /// <summary>
    /// Calculates the furthest point on the region 
    /// along a given direction.
    /// </summary>
    Vector3 GetFurthestPoint(Vector3 direction);
}